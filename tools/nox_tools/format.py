#!/usr/bin/env python3

from .git_utils import get_repo_sources
from .utils import (
    find_executable,
    run_command_result
)

CLANG_FORMAT_CMD = find_executable('clang-format')

def _check_prerequisites():
    """
    Check prerequisites necessary for running a command.

    Args:
        args:
            arguments parsed from command-line
    Returns:
        int:
            0 on success, 1 on failure
    """
    if any([CLANG_FORMAT_CMD is None]):
        print("Prerequisites not satisfied")
        return 1
    
    return 0

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
    if _check_prerequisites() == 1:
        return 1

    sources = get_repo_sources()
    cmd = f'"{CLANG_FORMAT_CMD}" -Werror --dry-run {sources}'
    return run_command_result(cmd)

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
    if _check_prerequisites() == 1:
        return 1

    sources = get_repo_sources()
    cmd = f'"{CLANG_FORMAT_CMD}" -Werror --i {sources}'
    return run_command_result(cmd)

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
