ARG TARGETARCH
# always build on the build machine's native architecture,
# cross-compiling for the target — no QEMU emulation needed
FROM --platform=$BUILDPLATFORM docker.io/gcc:16 AS builder
ARG TARGETARCH
WORKDIR /src
COPY --parents=true *.c *.h arch/*.h discard.ld Makefile /src
RUN case "$TARGETARCH" in \
      amd64) make ;; \
      arm64)  apt-get update && apt-get install -y --no-install-recommends \
                gcc-aarch64-linux-gnu libc6-dev-arm64-cross && \
              make TARGET=aarch64-linux-gnu- ;; \
      riscv64) apt-get update && apt-get install -y --no-install-recommends \
                gcc-riscv64-linux-gnu libc6-dev-riscv64-cross && \
              make TARGET=riscv64-linux-gnu- ;; \
      *) echo "unsupported TARGETARCH: $TARGETARCH" >&2; exit 1 ;; \
    esac

FROM scratch
COPY --from=builder /src/unemployd.stripped /unemployd
ENTRYPOINT ["/unemployd"]
