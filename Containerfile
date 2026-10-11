FROM docker.io/gcc:16 AS builder
WORKDIR /src
COPY *.c *.h *.ld Makefile /src
RUN make

FROM scratch
COPY --from=builder /src/idled.stripped /idled
ENTRYPOINT ["/idled"]
