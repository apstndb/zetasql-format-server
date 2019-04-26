package main

import (
    "fmt"
    "log"
    "net/http"
    "os"
    "os/exec"
)

func handler(w http.ResponseWriter, r *http.Request) {
    log.Print("zetasql-server received a request.")
    cmd := exec.Command("./bazel-bin/main")
    cmd.Stdin = r.Body
    cmd.Stdout = w
    cmd.Run()
}

func main() {
    log.Print("zetasql-server started.")

    http.HandleFunc("/", handler)

    port := os.Getenv("PORT")
    if port == "" {
        port = "8080"
    }

    log.Fatal(http.ListenAndServe(fmt.Sprintf(":%s", port), nil))
}
