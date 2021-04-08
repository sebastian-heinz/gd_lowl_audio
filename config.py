supported_platforms = ["windows", "osx", "linuxbsd", "server"]

def can_build(env, platform):
    return True


def configure(env):
    platform = env["platform"]

    if platform not in supported_platforms:
        raise RuntimeError("GD_LOWL_AUDIO - This module does not currently support building for this platform")

    pass
