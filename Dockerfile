FROM scratch
COPY adrift /
COPY *.txt /
CMD ["./adrift"]
