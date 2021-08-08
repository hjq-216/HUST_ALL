FROM alpine:3.12.0

COPY my-app/server /server
RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apk/repositories && \
        apk add go && go env -w GOPROXY=https://goproxy.cn,direct
