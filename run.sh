#!/bin/bash

_run_this() {
    local binary="main"
    if [[ "${1}" == 'c' ]] ; then
        make clean
    else
        make -j8
        ./"${binary}" --deploy-path / --docroot . --http-address 0.0.0.0 --http-port 9090
    fi
}

_run_this "${@}"
