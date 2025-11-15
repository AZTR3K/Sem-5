# Start from a slim Python 3.10 image
FROM python:3.10-slim

# Set the working directory
WORKDIR /app

# Copy the requirements file and install libraries
COPY requirements.txt .
RUN pip install -r requirements.txt

# Copy the rest of the web app's code
# This includes app.py and the 'templates' folder
COPY . .

# Expose the port Gunicorn will run on
EXPOSE 5000

# Use Gunicorn to run the app (production-ready)
CMD ["gunicorn", "--bind", "0.0.0.0:5000", "app:app"]
