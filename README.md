# mini-http

A minimal HTTP/1.1 server, written in C. Please don't regard this as a production-grade implementation of such a service; it merely acts as a toy project to enlarge my understanding of HTTP as well as improve my C programming capabilities.

Most of what I develop here is based on an (old) [blog post](https://www.jmarshall.com/easy/http/#http1.1s2) by James Marshall. He explains what is roughly necessary to reach HTTP/1.1 compliancy, though I will keep and eye on [RFC 2616](https://datatracker.ietf.org/doc/html/rfc2616). I will also try to find ways for additional verification, e.g. using `curl`.

## What currently works

- [X] Accept inbound HTTP connections (using `curl localhost:8080` and return status code 501 Not Implemented)
- [ ] Parse basic http requests

## Usage

The [`main.c`](./main.c) file serves as the entrypoint and binds the HTTP server socket on port specified by the `PORT` macro, defaulting to 8080.

```bash
make
./main
```

Then, open up another terminal:

```bash
curl -I localhost:8080
```

## License

MIT
