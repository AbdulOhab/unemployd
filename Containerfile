FROM docker.io/gcc:16 AS builder
WORKDIR /src
COPY --parents=true *.c *.h arch/*.h discard.ld Makefile /src
RUN make

FROM scratch
COPY --from=builder /src/unemployd.stripped /unemployd
ENTRYPOINT ["/unemployd"]
