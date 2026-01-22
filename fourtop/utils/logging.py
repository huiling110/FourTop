"""
Centralized Logging Setup
=========================

Standardized logging configuration for the FourTop analysis package.

Usage:
    from fourtop.utils.logging import setup_logger

    logger = setup_logger('stage4.templates')
    logger.info(f"Processing era {era}")
    logger.debug(f"Input directory: {input_dir}")
"""

import logging
import sys
from typing import Optional


def setup_logger(name: str, level: int = logging.INFO,
                 log_file: Optional[str] = None) -> logging.Logger:
    """
    Configure module logger with standard format.

    Args:
        name: Logger name (will be prefixed with 'fourtop.')
        level: Logging level (default: INFO)
        log_file: Optional file path for file logging

    Returns:
        Configured logger instance

    Example:
        >>> logger = setup_logger('stage4.templates')
        >>> logger.info("Processing started")
        [2024-01-15 10:30:45] [INFO] [fourtop.stage4.templates] Processing started
    """
    logger_name = f'fourtop.{name}' if not name.startswith('fourtop.') else name
    logger = logging.getLogger(logger_name)

    # Avoid adding handlers multiple times
    if logger.handlers:
        return logger

    logger.setLevel(level)

    # Console handler
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setLevel(level)

    # Format: [timestamp] [level] [module] message
    formatter = logging.Formatter(
        '[%(asctime)s] [%(levelname)s] [%(name)s] %(message)s',
        datefmt='%Y-%m-%d %H:%M:%S'
    )
    console_handler.setFormatter(formatter)
    logger.addHandler(console_handler)

    # Optional file handler
    if log_file:
        file_handler = logging.FileHandler(log_file)
        file_handler.setLevel(level)
        file_handler.setFormatter(formatter)
        logger.addHandler(file_handler)

    return logger


def get_logger(name: str) -> logging.Logger:
    """
    Get existing logger or create new one with default settings.

    Args:
        name: Logger name

    Returns:
        Logger instance
    """
    logger_name = f'fourtop.{name}' if not name.startswith('fourtop.') else name
    logger = logging.getLogger(logger_name)

    # If no handlers, set up with defaults
    if not logger.handlers:
        return setup_logger(name)

    return logger


def set_log_level(level: int) -> None:
    """
    Set log level for all fourtop loggers.

    Args:
        level: Logging level (e.g., logging.DEBUG, logging.INFO)
    """
    # Get root fourtop logger
    root_logger = logging.getLogger('fourtop')
    root_logger.setLevel(level)

    # Update all child loggers
    for handler in root_logger.handlers:
        handler.setLevel(level)
