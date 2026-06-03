#!/usr/bin/env bash

info() {
	echo "[INFO]" $@
}

error() {
	echo "[ERROR]" $@
}

main() {
	local max=${1}
	max=${max:=100}
	local NUMBERS=$(shuf -i 1-$max)
	info "Testing ${max} numbers..."
	./push_swap $NUMBERS | tee operations | ./checker_linux $NUMBERS | tee outfile
	wc -l operations
	local max_ops=${2}
	max_ops=${max_ops:=700}
	local opcount=$(wc -l operations | cut -f 1 -d ' ')
	[ "$opcount" -gt "$max_ops" ] && error "too many operations!" || info "all good!"
}

main $@
