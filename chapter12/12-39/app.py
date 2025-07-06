def app(environ, start_response):
    body = b"Hello from Gunicorn!\n"
    headers = [
        ("Content-Type", "text/plain"),
        ("Content-Length", str(len(body)))
    ]
    start_response("200 OK", headers)
    return [body]
