FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    make \
    g++ \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN make

CMD ["./mysh"]