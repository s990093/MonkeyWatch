.PHONY: git run 

SERIAL_PORT := /dev/cu.usbserial-10

git:
	git add .
	git commit -m "New commit"
	git push


build:
	python setup.py py2app
