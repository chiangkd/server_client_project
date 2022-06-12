int main() {

    char buff[500];
    sprintf(buff, "HTTP/1.1 200 OK\r\n%s%s%s%s%s",
			"Content-Type: text/html\r\n\r\n",
			"<html><head><style>",
			"body{font-family: monospace; font-size: 13px;}",
			"td {padding: 1.5px 6px;}",
			"</style></head><body>");
    sprintf(buff, "<table>");
    puts(buff);
    return 0;
}