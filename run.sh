#!/bin/bash

_run_this() {
    local binary="main"
    if [[ "${1}" == 'c' ]] ; then
        make clean
    else
        if make -j8 ; then
            ./"${binary}" --deploy-path / --docroot / --http-address 0.0.0.0 --http-port 9090
        else
            echo "Error....."
        fi
    fi
}

_run_this "${@}"
