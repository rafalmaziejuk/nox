import git
import pathlib

def get_repo_sources():
    """
    Returns paths to all relevant source files in this repository.

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
    
    repo = git.Repo('.', search_parent_directories=True)
    repo_root_dir = repo.working_tree_dir

    sources = []
    for dir in dirs:
        dir_path = pathlib.Path(repo_root_dir) / dir
        sources += [str(path)
                    for path in dir_path.rglob('*')
                    if path.suffix in extensions and path.stem not in exceptions]

    return ' '.join(sources)
