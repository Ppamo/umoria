FROM docker.io/alpine:3.11 AS builder
WORKDIR /source
COPY . /source
RUN apk update && apk upgrade && apk add git make cmake g++ pulseaudio-dev ncurses-dev
RUN mkdir /build && cmake -D build_dir=/build . && make

FROM docker.io/alpine:3.11
WORKDIR /app
COPY --from=builder /build /app
RUN apk update && apk upgrade && apk add g++ ncurses-dev
CMD ["/app/umoria"]
