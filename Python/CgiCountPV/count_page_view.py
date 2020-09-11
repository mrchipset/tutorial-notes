#!/usr/bin/python3

import cgi


def main():
    form = cgi.FieldStorage()
    site_url = form.getvalue('url')
    print('Content-type: text/plain\r\n')
    print(site_url)


if __name__ == '__main__':
    main()
