#!/bin/bash

_run_this() {
    local binary="main"
    make -j8
    ./"${binary}" --deploy-path / --docroot . --http-address 0.0.0.0 --http-port 9090
}

_run_this "${@}"
