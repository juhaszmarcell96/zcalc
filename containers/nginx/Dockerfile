FROM nginx:latest

# Copy SSL certificates
COPY nginx.crt /etc/ssl/certs/nginx.crt
COPY nginx.key /etc/ssl/private/nginx.key
COPY nginx.conf /etc/nginx/nginx.conf

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]
