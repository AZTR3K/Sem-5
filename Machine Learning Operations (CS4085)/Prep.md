# Final MLOps Prep

## 1. Data Engineering in Pandas/Numpy
### Handling Missing Values
```py
# Fill numeric columns with median
numeric_cols = df.select_dtypes(include=[np.number]).columns

for col in numeric_cols:
    median_val = df[col].median()
    df[col] = df[col].fillna(median_val)

# Fill categorical columns with mode
categorical_cols = df.select_dtypes(include=["object", "category"]).columns

for col in categorical_cols:
    mode_val = df[col].mode()[0]
    df[col] = df[col].fillna(mode_val)

# Simple Imputer
num_imputer = SimpleImputer(strategy="median")
df[[col1, col2]] = num_imputer.fit_transform(df[[col1, col2]])
```

### Handling Categorical Data
#### Label Encoding
##### What it does
- Converts categories into integer labels.
- ["Low", "Medium", "High"] -> [0, 1, 2]

##### When to use Label Encoding
- The feature is ordinal. (Low < Medium < High)
- Tree based models -> Decision Trees, Random Forest, XGBoost/LightGBM
- Do not use label encoding for nominal data with linear models (Logistic Regression, SVM, kNN)

##### Basic Syntax
```py
# Scikit-Learn
le = LabelEncoder()

data = ["Low", "Medium", "High"]
encoded = le.fit_transform(data)
```

#### One-Hot Encoding
##### What it does
- Creates binary columns for each category.
- Color = ["Red", "Blue", "Green"]
- Red Blue Green: 1 0 0

##### When to use One-Hot Encoding
- The feature is nominal (no order)
- Using distance-based or linear models (Logistic Regression, Linear Regression, SVM, kNN)
- Do not one-hot encode very high-cardinality features (thousands of unique values)

##### Basic Syntax
```py
# Pandas
df_encoded = pd.get_dummies(df, columns=[col1, col2])

# Scikit-Learn
ohe = OneHotEncoder(sparse=False)

data = [["Red"], ["Blue"], ["Green"]]
encoded = encoder.fit_transform(data)
```

### Detecting and Removing Outliers
#### Z-score
```py
df = df[(np.abs(stats.zscore(df["price"])) < 3)]
```

#### IQR
```py
Q1 = df.quantile(0.25)
Q3 = df.quantile(0.75)
IQR = Q3 - Q1

df_clean = df[~((df < (Q1 - 1.5 * IQR)) | (df > (Q3 + 1.5 * IQR))).any(axis=1)]
```

#### Correlation
```py
import pandas as pd
import numpy as np

# target column name
target = "target"

# correlation with target
corr = df.corr(numeric_only=True)[target].abs()

# select features above threshold
threshold = 0.3
selected_features = corr[corr > threshold].index.drop(target)

# remove highly correlated features (optional)
corr_matrix = df[selected_features].corr().abs()
upper = corr_matrix.where(np.triu(np.ones(corr_matrix.shape), k=1).astype(bool))
to_drop = [col for col in upper.columns if any(upper[col] > 0.8)]

# final selected dataframe
df_selected = df[selected_features.drop(to_drop).tolist() + [target]]
```

## 2. Machine Learning
### Model Evaluation Classification
#### Accuracy:
$\frac{TN + TP}{TN + FP + TP + FN}$
#### Precision:
$\frac{TP}{TP + FP}$
#### Recall:
$\frac{TP}{TP + FN}$
#### F1 Score:
2 * $\frac{Precision * Recall}{Precision + Recall}$

### Scaling Numeric Features
```py
scaler = StandardScaler()
x_num = scaler.fit_transform(df[[col1, col2]])
```

### Train-test Split
```py
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)
```

### Classification
#### Train models and evaluate
```py
models = {
    "LogisticRegression" : LogisticRegression(max_iter=1000, random_state=42),
    "SVM" : SVC(probability=True, random_state=42),
    "KNN" : KNeighborsClassifier(),
    "DecisionTree" : DecisionTreeClassifier(random_state=42),
    "RandomForest" : RandomForestClassifier(n_estimators=200, random_state=42)
}

for name, model in models.item():
    model.fit(X_train, y_train)
    y_pred = model.predict(X_test)

    acc = accuracy_score(y_test, y_pred)
    prec = precision_score(y_test, y_pred, average="macro", zero_division=0)
    rec = recall_score(y_test, y_pred, average="macro", zero_division=0)
    f1 = f1_score(y_test, y_pred, average="macro", zero_division=0)
```

### Regression
#### Distinguishing Columns
```py
numeric_features = df.select_dtypes(include=[np.number]).columns.tolist()
categorical_features = df.select_dtypes(exclude=[np.number]).columns.tolist()
```

#### Pipelining
```py
# Numeric Pipeline
numeric_pipeline = Pipeline([
    ("imputer", SimpleImputer(strategy="median")),
    ("scaler", StandardScaler())
])

# Categorical Pipeline
categorical_pipeline = Pipeline([
    ("imputer", SimpleImputer(strategy="most_frequent")),
    ("encoder", LabelEncoder())
])
```

#### Transformers
```py
preprocess = ColumnTransformer([
    ("num", numeric_pipeline, numeric_features),
    ("cat", categorical_pipeline, categorical_features)
], remainder="drop")
```

#### Feature Selection
```py
feature_selector = SelectKBest(mutual_info_regression, k=12)
```

#### Implementation
```py
X_train_prep = preprocess.fit_transform(X_train)
X_test_prep = preprocess.fit_transform(X_test)

X_train_sel = feature_selector.fit_transform(X_train_prep, y_train)
X_test_sel = feature_selector.transform(X_test_prep)
```

#### Model
```py
lr = LinearRegression()
lr.fit(X_train_sel, y_train)
t_pred_lr = lr.predict(X_test_sel)

mae = mean_absolute_error(y_test, y_pred_lr)
mse = mean_squared_error(y_test, y_pred_lr)
rmse_lr = np.sqrt(mse_lr)
```

## 3. Deep Learning
### Fine Tuning
- Freezing unfreezing layers of a large model to match your specific use case.

```py
conv_base.trainable = True
set_trainable = False
for layer in conv_base.layers:
    if layer.name == "block5_conv1":
        set_trainable = True
    if set_trainable:
        layer.trainable = True
    else:
        layer.trainable = False
```

### Model Building
#### ANN
```py
model = Sequential()
model.add(Flatten(input_shape=(28, 28)))   # Input Layer
model.add(Dense(128, activation="relu"))   # Hidden Layer
model.add(Dense(64, activation="relu"))    # Hidden Layer
model.add(Dense(10, activation="softmax")) # Output Layer

model.compile(
    optimizer="adam",
    loss="categorical_crossentropy",
    metrics=["accuracy"]
)

model.fit(X_train, y_train, validation_data=(X_test, y_test), epochs=10, batch_size=32)
```

#### CNN
```py
model = Sequential()
# 1. Convolutional Layers
model.add(Conv2D(28, (3, 3), input_shape=(28, 28, 1), activation="relu"))
model.add(MaxPooling2D(2, 2))
model.add(Conv2D(16, (3, 3), activation="relu"))
model.add(MaxPooling2D(2, 2))

# 2. Flatten Layers
model.add(Flatten())

# 3. ANN Layers
model.add(Dense(128, activation="relu"))
model.add(Dense(64, activation="sigmoid"))
model.add(Dense(10, activation="softmax"))

model.compile(optimizer="adam", loss="categorical_crossentropy", metrics=["accuracy"])

model.fit(X_train, y_train, validation_data=(X_test, y_test), epochs=10, batch_size=32)
```

## 4. Flask
### Creating an App
```py
app = Flask(__name__)

if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)
```

### Create a route
```py
@app.route("/")
def hello_world():
    return "<h1>Hello, World! Welcome to Flask.</h1>"
```

### Render an html template
```py
@app.route("/")
def home():
    return render_template("index.html")
```

### Sending data from flask to html
```py
@app.route("/user")
def user():
    name = "Usman"
    return render_template("user.html", username=name)
```

### Handling POST request
```py
@app.route("/submit", methods=["POST"])
def submit():
    user_name = request.form["user_name"]
    return render_template("result.html", name=user_name)
```

## 5. Versioning
### GitHub
#### Setup Id
```sh
git config --global user.name "Your Name"
git config --global user.email "youremail@example.com"
```

#### Initialise git
```sh
git init
```

#### Basic commands
```sh
git branch                      # displays current branch
git remote -v                   # remote path of repository
git branch -m main
git remote add origin url       # add remote GitHub link
git checkout -b main            # ensure branch is main
git add file_name               # stage the folder/file or . current
git commit -m "First Commit 01" # message telling what changes have been made
git push -u origin main         # push staged content to remote repo
git pull origin main            # download new changes from the remote repo
git clone url                   # copies an entire remote repo to your local machine for the first time
git merge main                  # merge feature from other branch to main branch
```

### DVC
#### Basic Commands
```sh
dvc status                           # check the status of data, if data changes
git add data.dvc                     # commit changes to git
dvc commit                           # commit this change to sync data.dvc file
dvc remote add -d gdrive gdrive_link # configure remote storage for dvc
dvc push                             # push to remote repo
```

#### Pipeline
##### Configuration file: params.yaml
```yaml
data:
    raw_path: data/raw/dataset.csv
    processed_path: data/processed/
    test_size: 0.2
    seed: 43

train:
    epochs: 50
    batch_size: 32
    learning_rate: 0.001

model:
    type: random_forrest
    n_estimators: 100
    max_depth: 10
```

##### Pipeline file: dvc.yaml
```yaml
stages:
    # Stage 1: Data Preparation
    prepare:
        cmd: python src/prepare.py
        deps:
            - src/prepare.py
            - data/raw/dataset.csv
        params:
            - data.test_size
            - data.seed
        outs:
            - data/processed/train.csv
            - data/processed/test.csv

    # Stage 2: Training
    train:
        cmd: python src/train.py
        deps:
            - src/train.py
            - data/processed/train.csv
        params:
            - train.epochs
            - train.batch_size
            - model.type
        outs:
            - models/model.pkl

    # Stage 3: Evaluation
    evaluate:
        cmd: python src/evaluate.py
        deps:
            - src/evaluate.py
            - models/model.pkl
            - data/processed/test.csv
        methods:
            - metrics.json:
                cache: false
```

##### To run the pipeline
```sh
dvc repro
```

## 6. MLFlow
### Integrating MLFlow with DagsHub and Creating a REST API
#### Setup MLFlow Tracking on DagsHub
```py
# Initialise tracking uri and credentials in your python script:
dagshub.init(repo_owner="<owner>", repo_name="mlflow-demo", mlflow=True)

# Or manually set MLFlow tracking URI
mlflow.set_tracking_uri("https://dagshub.com/<username>/mlflow-demo.mlflow")

# If the repository is private
os.environ["MLFLOW_TRACKING_USERNAME"] = "<username>"
os.environ["MLFLOW_TRACKING_PASSWORD"] = "<password>"
```

#### Train and log model
```py
with mlflow.start_run():
    model = LinearRegression()
    model.fit(X_train, y_train)

    preds = model.predict(X_test)
    mse = mean_squared_error(y_test, preds)

    mlflow.log_param("test_size", 0.2)
    mlflow.log_metric("mse", mse)
    mlflow.sklearn.log_model(model, "model")
```

#### Create REST API to Serve Model
```py
app = FastAPI(title="MLFlow Model API")

class InputData(BaseModel):
    x: float

@app.post("/predict")
def predict(data: InputData):
    prediction = model.predict([data.x]])
    return {"prediction": prediction[0]}
```

#### To run the API:
```sh
uvicorn app:app --reload
```

## 7. Docker
### Dockerfile
```dockerfile
# Small python base image
FROM python:3.11-slim
# Copy current directory contents to leverage Docker cache
COPY . /app
# Set working directory
WORKDIR /app
# Install dependencies
RUN pip install -r requirements
# Command to run app.py file
CMD python app.py
```

### Important Commands
```sh
docker -v                              # check docker version
docker pull docker/getting-started     # pull container from dockerHub
docker images                          # check docker images
docker ps                              # running images
docker stop [container_id]             # stop container by id
docker build -t [image_name] .         # build image from directory
docker run -p 5000:5000 welcome-app    # run a container
docker run --rm -p 5000:500 welcomeapp # run a container 2
docker logs container_id               # view logs of container by id
docker login                           # login to dockerHub
docker image rm -f [image_name]        # removes an image
docker build -t [repository_name] .    # built a docker image
docker push [repository_name]          # push container to dockerHub
```

### Compose.yaml
```yaml
version: "3.8"

services:
    db:
        image: postgres:13
        volumes:
            - db_data:/var/lib/postgresql/data
        environment:
            - POSTGRES_USER=user
            - POSTGRES_PASSWORD=pass
            - POSTGRES_DB=mydb
        networks:
            - backend_net
    web:
        build: .
        ports:
            - "8000:8000"
        volumes:
            - .:/app
        environment:
            - DATABASE_URL=postgresql://user:pass@db:5432/mydb
        depends_on:
            - db
        networks:
            - backend_net

    volumes:
        db_data:

    networks:
        backend_net:
```

## 8. Airflow
### DAG
```py
dag = DAG(
    dag_id="simple_dag",
    start_date=datetime(2024, 1, 1),
    schedule="@daily"
)
```

### Task
#### Python Operator
```py
def greet():
    print("Hello from Airflow Task!")

# Task 1
task_python = PythonOperator(
    task_id="greet_task",
    python_callable=greet,
    dag=dag,
)
```

#### Bash Operator
```py
task_bash = BashOperator(
    task_id="run_shell_command",
    bash_command="echo 'Hello from the terminal'"
    dag=dag
)
```

#### Email Operator
```py
task_email = EmailOperator(
    task_id="send_notification",
    to="manager@example.com",
    subject="Airflow Alert",
    html_content="<h3>The pipeline finished successfully.</h3>",
    dag=dag
)
```

#### S3 To GCS Operator
```py
task_move_data = S3ToGCSOperator(
    task_id="s3_to_gcs",
    bucket="my-aws-bucket",          # Source S3 bucket
    prefix="data/files/",            # Source folder/files
    dest_gcs="gs://my-gcs-bucket/",  # Destination GCS bucket
    dag=dag
)
```

#### Docker Operator
```py
task_docker = DockerOperator(
    task_id="run_in_container",
    image="python:3.9-slim",
    command="python -c 'print(\"I am running inside an isolated container\")'",
    network_mode="bridge",
    dag=dag
)
```

#### Kubernetes Pod Operator
```py
task_k8s = KubernetesPodOperator(
    task_id="run_on_k8s",
    name="my-pod-runner",
    image="ubuntu:latest",
    cmds=["echo", "Hello from inside the Kubernetes Cluster"],
    dag=dag
)
```

### Scheduler
```py
dag = DAG(
    dag_id="ml_training_daily",
    schedule="@daily",
)
# @daily, @weekly, @yearly, @monthly, @hourly
# schedule="30 8 * * 1-5" will run every weekday (Mon-Fri) at 8:30 AM.
```

### Airflow commands
```sh
astro dev init
astro dev start
astro dev stop
```

### Task order in Dag Pipeline
```py
task1 >> task2 >> task3
```

### XCom
```py
def send_data(ti):
    # Method 1: Explicit Push
    ti.xcom_push(key="my_key", value="Secret Password")

    # Method 2: Implicit Push
    return "Standard Data"

def receive_data(ti):
    # Pull specific key from specific task
    secret = ti.xcom_pull(key="my_key", task_ids="sender_task")

    # Pull return value
    standard = ti.xcom_pull(task_ids="sender_task")

    print(f"I received: {secret} and {standard}")

t1 = PythonOperator(
    task_id="sender_task",
    python_callable=send_data,
    dag=dag
)

t2 = PythonOperator(
    task_id="receiver_task",
    python_callable=receive_data,
    dag=dag
)

t1 >> t2
```
