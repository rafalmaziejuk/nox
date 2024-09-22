import git

def get_repo_root_dir():
    """
    Returns a root directory of this repository.

    Returns:
        str:
            repository root directory
    """
    repo = git.Repo('.', search_parent_directories=True)
    return repo.working_tree_dir
