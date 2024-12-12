#!/bin/sh

# Disabling annoying shit because i wanna glob babyyyyyyyyyyyyyyyy
# using $pargs gotta glob unless using xargs don't feel like it iagjsdijfiasjfiasidfj
# posix compliant waht???????
# shellcheck disable=SC2086

_check_args() {
    [ "$#" -le 1      ] && return 1
    [ "${1}" = "${2}" ] && return 0
    _c="${1}"
    shift 2
    _check_args "${_c}" "${@}"
}
_run_this() {
    _pargs='--docroot / --deploy-path / --http-address 0.0.0.0  --http-port 9090'
    binary="main"
    if _check_args '-c' "${@}" ; then
        make clean
    elif _check_args '-v' "${@}" ; then
        valgrind ./"${binary}" $_pargs
    else
        if make -j8 2>log.txt ; then
            ./"${binary}" $_pargs
        else
            echo "Error....."
            _check_args '-l' "${@}" && ${PAGER} 'log.txt'
        fi
    fi
}

_run_this "${@}"
