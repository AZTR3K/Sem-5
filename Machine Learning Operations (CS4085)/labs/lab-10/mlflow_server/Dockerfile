# Use python 3.10 as the base image
FROM python:3.10

# Set the working directory inside the container
WORKDIR /mlflow

# Install MLflow and psycopg2-binary
RUN pip install mlflow==2.14 psycopg2-binary boto3

# Expose the port MLflow uses
EXPOSE 5000

# Copy the entrypoint script into the image
COPY entrypoint.sh .

# Make the entrypoint script executable
RUN chmod +x entrypoint.sh

# Set the default command to run the script
CMD ["./entrypoint.sh"]
