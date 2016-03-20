import logging
import logging.handlers
from logging import DEBUG,INFO,WARNING,ERROR,CRITICAL


LOGFILE = 'runtime.log'

_logrotate = logging.handlers.RotatingFileHandler(
        LOGFILE, backupCount=2, delay=True)
_logrotate.setFormatter(
        logging.Formatter(
            '%(asctime)s %(levelname)-4.4s %(name)-20s: %(message)s'))
# Force a log rotation each time we start up
_logrotate.doRollover()

def getLogger(name):
    logger = logging.getLogger(name)
    logger.addHandler(_logrotate)

    logger.setLevel(DEBUG)

    return logger

