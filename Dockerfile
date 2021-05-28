FROM alpine:3.13
WORKDIR /app
COPY . .
RUN apk add --no-cache gcc musl-dev g++ make && make adrift
CMD ["./adrift"]