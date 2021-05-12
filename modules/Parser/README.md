# How Parse works ?

# Example request http

```
POST http://www.domain.com/index.html*?name1=value1&name2=value2 HTTP/1.1
User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
Host: www.tutorialspoint.com
Content-Type: text/xml; charset=utf-8
Content-Length: length
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive

<?xml version="1.0" encoding="utf-8"?>
<string xmlns="http://clearforest.com/">string</string>
```

# Parse

## IP :
`www.tutorialspoint.com` 

*(if ip localhost:port)*

`localhost`

## Method :
`POST`

## Protocol :
`HTTP/1.1`

## URL :
`http://www.domain.com/index.html*?name1=value1&name2=value2`

## Argument (key: value) :
```
name1: value1
name2: value2
```

## Header (key: value) :
```
User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)
Host: www.tutorialspoint.com
Content-Type: text/xml; charset=utf-8
Content-Length: length
Accept-Language: en-us
Accept-Encoding: gzip, deflate
Connection: Keep-Alive
```

## Body
```
<?xml version="1.0" encoding="utf-8"?>
<string xmlns="http://clearforest.com/">string</string>
```