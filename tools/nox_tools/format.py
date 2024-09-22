#!/usr/bin/env python3

import pathlib
import subprocess

from .git_utils import get_repo_root_dir

CLANG_FORMAT_CMD = 'clang-format'

def _get_sources():
    """
    Returns paths to source files in this repository that have to be formatted.

    Returns:
        str:
            space-delimited string that contains paths to source files
    """
    extensions = ('.cpp', 
                  '.h', 
                  '.inl')
    exceptions = ('export.h')
    dirs = ('include',
            'sandbox',
            'src',
            'tests')
    repo_root_dir = get_repo_root_dir()

    sources = []
    for dir in dirs:
        dir_path = pathlib.Path(repo_root_dir) / dir
        sources += [str(path)
                    for path in dir_path.rglob('*')
                    if path.suffix in extensions and path.stem not in exceptions]

    return ' '.join(sources)

def _check(args):
    """
    Runs clang-format check on all sources in this repository.

    Args:
        args:
            arguments parsed from command-line
    Returns:
        int:
            0 on success, 1 on failure
    """
    sources = _get_sources()
    cmd = f"{CLANG_FORMAT_CMD} -Werror --dry-run {sources}"
    try:
        result = subprocess.run(cmd, capture_output=True, shell=True)
        if result.returncode != 0:
            print(result.stderr.decode('utf-8'))
            return 1
    except subprocess.CalledProcessError:
        print('clang-format check failed to run')
        return 1

    return 0

def _fix(args):
    """
    Runs clang-format in place fix on all sources in this repository.

    Args:
        args:
            arguments parsed from command-line
    Returns:
        int:
            0 on success, 1 on failure
    """
    sources = _get_sources()
    cmd = f"{CLANG_FORMAT_CMD} -Werror --i {sources}"
    try:
        result = subprocess.run(cmd, capture_output=True, shell=True)
        if result.returncode != 0:
            print(result.stderr.decode('utf-8'))
            return 1
    except subprocess.CalledProcessError:
        print('clang-format fix failed to run')
        return 1

    return 0

def add_subparsers(subparsers):
    """
    Adds subparsers to the main parser.

    Args:
        subparsers:
            main parser subparsers
    """
    format_parser = subparsers.add_parser('format', help='Format code via clang-format')
    format_parser.set_defaults(func=lambda x: format_parser.print_help())

    format_subparsers = format_parser.add_subparsers(help='Format subcommands (<subcommand> -h for subcommand help)',
                                                     dest='command')

    format_check_parser = format_subparsers.add_parser("check", help="Check sources formatting")
    format_check_parser.set_defaults(func=_check)

    format_fix_parser = format_subparsers.add_parser("fix", help="Fix sources formatting")
    format_fix_parser.set_defaults(func=_fix)
