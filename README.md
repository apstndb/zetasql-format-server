# zetasql-format-server

It is GoogleSQL dialect format server using ZetaSQL. It runs on Cloud Run(and Knative Serving).

[![Run on Google Cloud](https://storage.googleapis.com/cloudrun/button.png)](https://console.cloud.google.com/cloudshell/editor?shellonly=true&cloudshell_image=gcr.io/cloudrun/button&cloudshell_git_repo=https://github.com/apstndb/zetasql-format-server.git)
(Note: It takes over 10 minutes in Cloud Build.)

## Usage

```sh
$ SERVICE_URL=$(gcloud beta run services describe --format="value(status.domain)" ${REPO_NAME})
$ curl ${SERVICE_URL} --data 'SELECT * FROM tbl'
SELECT
  *
FROM
  tbl
```

## References

- https://github.com/google/zetasql/
- https://github.com/jamesward/cloud-run-button