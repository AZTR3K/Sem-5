import os
import mlflow
import pandas as pd
from flask import Flask, request, render_template
from pymongo import MongoClient
import logging

# --- App & DB Setup ---
app = Flask(__name__)

# Configure Flask's logger to be visible in Gunicorn
gunicorn_logger = logging.getLogger('gunicorn.error')
app.logger.handlers = gunicorn_logger.handlers
app.logger.setLevel(logging.INFO)

try:
    MONGO_URI = os.environ.get("MONGO_URI", "mongodb://mongo:27017/")
    client = MongoClient(MONGO_URI)
    db = client.student_db
    collection = db.predictions
    app.logger.info("--- Flask App Initialized & Connected to MongoDB ---")
except Exception as e:
    app.logger.error(f"--- ERROR: Could not connect to MongoDB: {e} ---")

# --- MLflow Setup ---
MLFLOW_TRACKING_URI = os.environ.get(
    "MLFLOW_TRACKING_URI", "http://mlflow:5000")
mlflow.set_tracking_uri(MLFLOW_TRACKING_URI)
app.logger.info(f"--- MLflow Tracking URI set to: {MLFLOW_TRACKING_URI} ---")

# Load model globally, but do it ONCE, on the first request.
model = None


def load_model():
    """Load the latest model from MLflow."""
    global model
    if model is not None:
        app.logger.info("--- Model is already loaded. ---")
        return

    try:
        experiment_name = "Student Performance"
        app.logger.info(f"--- Searching for experiment: {experiment_name} ---")
        runs = mlflow.search_runs(
            experiment_names=[experiment_name],
            order_by=["start_time DESC"],
            max_results=1
        )

        if len(runs) == 0:
            app.logger.warning(
                "--- WARNING: No runs found in MLflow. Model remains 'None'. ---")
            return

        latest_run_id = runs.iloc[0].run_id
        model_uri = f"runs:/{latest_run_id}/student_pass_model"
        app.logger.info(f"--- Found model. Loading from URI: {model_uri} ---")
        model = mlflow.pyfunc.load_model(model_uri)
        app.logger.info(
            f"--- SUCCESSFULLY LOADED MODEL (Run ID: {latest_run_id}) ---")

    except Exception as e:
        app.logger.error(f"--- !!! ERROR LOADING MODEL: {e} !!! ---")
        import traceback
        app.logger.error(traceback.format_exc())  # Print full error stack


# --- Flask Routes ---
@app.route('/')
def home():
    """Render the home page."""
    return render_template('index.html')


@app.route('/predict', methods=['POST'])
def predict():
    """Handle prediction requests."""
    global model

    # Try to load the model if it's not loaded.
    if model is None:
        app.logger.info("--- 'model' is None, attempting to load... ---")
        load_model()

    # If it's *still* not loaded (e.g., trainer hasn't run), return an error.
    if model is None:
        app.logger.error(
            "--- Model is still 'None' after load attempt. Check logs. ---")
        return render_template('index.html', prediction_text="Model is not available. Please run the trainer and check logs.")

    try:
        # Get data from the form
        study_hours = float(request.form['study_hours'])
        sleep_hours = float(request.form['sleep_hours'])

        # Create a DataFrame for the model
        data = pd.DataFrame([[study_hours, sleep_hours]], columns=[
                            'study_hours', 'sleep_hours'])

        # Make a prediction
        app.logger.info("--- Making prediction... ---")
        prediction = model.predict(data)[0]
        result_text = "Passed" if prediction == 1 else "Failed"
        app.logger.info(f"--- Prediction: {result_text} ---")

        # --- Store in MongoDB ---
        record = {
            "study_hours": study_hours,
            "sleep_hours": sleep_hours,
            "prediction": result_text
        }
        collection.insert_one(record)
        app.logger.info("--- Prediction saved to MongoDB ---")

        return render_template('index.html', prediction_text=f"Prediction: You {result_text}")

    except Exception as e:
        app.logger.error(f"--- !!! ERROR DURING PREDICTION: {e} !!! ---")
        return render_template('index.html', prediction_text=f"Error: {e}")
