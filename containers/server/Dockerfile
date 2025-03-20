FROM python:3.10

WORKDIR /app

COPY server.py /app/
RUN pip install websockets

EXPOSE 4444

CMD ["python", "server.py"]
