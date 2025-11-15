#!/bin/bash
# File: mlflow_server/entrypoint.sh

echo "Starting MLflow Tracking Server..."

# Create a 'db' directory inside the WORKDIR
mkdir -p /mlflow/db

mlflow server \
    --backend-store-uri sqlite:////mlflow/db/mlflow.db \
    --default-artifact-root /mlflow/artifacts \
    --serve-artifacts \
    --host 0.0.0.0 \
    --port 5000
