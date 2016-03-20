import logging
import logging.handlers
from logging import DEBUG,INFO,WARNING,ERROR,CRITICAL


LOGFILE = 'runtime.log'

_logrotate = logging.handlers.RotatingFileHandler(
        LOGFILE, maxBytes=1024*1024, backupCount=2)
_logrotate.setFormatter(
        logging.Formatter(
            '%(asctime)s %(levelname)-4.4s %(name)-20s: %(message)s'))

def getLogger(name):
    logger = logging.getLogger(name)
    logger.addHandler(_logrotate)

    logger.setLevel(DEBUG)

    return logger

