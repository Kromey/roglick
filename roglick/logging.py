import logging
from logging import DEBUG,INFO,WARNING,ERROR,CRITICAL


logging.basicConfig(
        filename='runtime.log',
        level=DEBUG,
        format='%(asctime)s %(name)-20s %(levelname)-4s: %(message)s',
        datefmt='%Y%m%d.%H%M%S')

def getLogger(name):
    logger = logging.getLogger(name)

    return logger

