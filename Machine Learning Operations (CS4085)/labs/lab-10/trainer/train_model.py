import pandas as pd
import mlflow
import mlflow.sklearn
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

# 1. Set the MLflow tracking URI
# This points to the service name 'mlflow' in our compose.yaml
mlflow.set_tracking_uri("http://mlflow:5000")

# 2. Start an MLflow experiment
mlflow.set_experiment("Student Performance")

print("Starting training script...")

try:
    # 3. Load the dataset
    # The CSV is mounted at /app/student_performance.csv in the container
    data = pd.read_csv("/app/student_performance.csv")

    # 4. Prepare data for training
    X = data[['study_hours', 'sleep_hours']]
    y = data['passed']
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=42)

    # 5. Start a single MLflow run
    with mlflow.start_run() as run:
        print(f"Starting run: {run.info.run_id}")

        # 6. Train the model
        model = LogisticRegression()
        model.fit(X_train, y_train)
        predictions = model.predict(X_test)

        # 7. Log parameters, metrics, and the model
        accuracy = accuracy_score(y_test, predictions)

        mlflow.log_param("solver", model.solver)
        mlflow.log_metric("accuracy", accuracy)

        # Log the model itself
        mlflow.sklearn.log_model(model, "student_pass_model")

        print(f"Logged model with accuracy: {accuracy}")
        print("Model training complete.")

except Exception as e:
    print(f"An error occurred: {e}")
