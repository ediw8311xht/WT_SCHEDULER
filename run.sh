#!/bin/sh

_check_args() {
    [ "$#" -le 1      ] && return 1
    [ "${1}" = "${2}" ] && return 0
    _c="${1}"
    shift 2
    _check_args "${_c}" "${@}"
}
_run_this() {
    binary="main"
    if _check_args '-c' "${@}" ; then
        make clean
    elif make -j8 2>log.txt ; then
        ./"${binary}"               \
            --docroot /             \
            --deploy-path /         \
            --http-address 0.0.0.0  \
            --http-port 9090
    else
        echo "Error....."
        _check_args '-l' "${@}" && ${PAGER} 'log.txt'
    fi
}

_run_this "${@}"
