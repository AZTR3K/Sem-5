# Start from a slim Python 3.10 image
FROM python:3.10-slim

# Set the working directory
WORKDIR /app

# Copy the requirements file and install libraries
COPY requirements.txt .
RUN pip install -r requirements.txt

# Copy the training script
COPY train_model.py .

# Set the default command to run the script
CMD ["python", "train_model.py"]
