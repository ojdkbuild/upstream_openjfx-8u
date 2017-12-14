# Copyright (C) 2009, 2016 Apple Inc. All rights reserved.
import unittest
from webkitpy.common.net.bugzilla import Attachment  # FIXME: This should not be needed

    process.communicate()  # ignore output
        test_object.temp_directory = os.path.realpath(tempfile.mkdtemp(suffix="svn_test"))
        self.dev_null = open(os.devnull, "w")  # Used to make our Popen calls quiet.
        input_process = subprocess.Popen(['echo', 'foo\nbar'], stdout=subprocess.PIPE, stderr=self.dev_null)  # grep shows usage and calls exit(2) when called w/o arguments.
        git_failure_message = "Merge conflict during commit: Your file or directory 'WebCore/ChangeLog' is probably out-of-date: resource out of date; try updating at /usr/local/libexec/git-core//git-svn line 469"
        svn_failure_message = """svn: Commit failed (details follow):
    def _shared_test_untracked_files(self, scm):
        write_into_file_at_path("test_file_new", "new content")
        self.assertItemsEqual(scm.untracked_files(), ["test_file_new"])

        os.mkdir("test_dir_new")
        write_into_file_at_path(os.path.join("test_dir_new", "test_file_new"), "new stuff")
        self.assertItemsEqual(scm.untracked_files(), ["test_dir_new", "test_file_new"])

        old_cwd = os.getcwd()
        os.chdir("test_dir_new")
        # Validate that untracked_files do not change with our cwd.
        self.assertItemsEqual(scm.untracked_files(), ["test_dir_new", "test_file_new"])

        os.chdir(old_cwd)

        write_into_file_at_path("test_file_new.pyc", "new ignored file")
        self.assertItemsEqual(scm.untracked_files(), ["test_dir_new", "test_file_new"])
        self.assertItemsEqual(scm.untracked_files(include_ignored_files=True), ["test_file_new.pyc", "test_dir_new", "test_file_new"])

        shutil.rmtree("test_dir_new")
        os.remove("test_file_new")
        os.remove("test_file_new.pyc")

    def _shared_test_discard_untracked_files(self, scm):
        write_into_file_at_path("test_file_new", "new content")
        os.mkdir("test_dir_new")
        write_into_file_at_path("test_dir_new/test_file_new", "new stuff")
        self.assertItemsEqual(scm.untracked_files(), ["test_dir_new", "test_file_new"])
        scm.discard_untracked_files()
        self.assertItemsEqual(scm.untracked_files(), [])

        write_into_file_at_path("test_file_new.pyc", "new content")
        self.assertItemsEqual(scm.untracked_files(True), ["test_file_new.pyc"])
        scm.discard_untracked_files(discard_ignored_files=False)
        self.assertItemsEqual(scm.untracked_files(True), ["test_file_new.pyc"])
        scm.discard_untracked_files(discard_ignored_files=True)
        self.assertItemsEqual(scm.untracked_files(True), [])

        if os.path.isdir("test_dir_new"):
            shutil.rmtree("test_dir_new")
        if os.path.isfile("test_file_new"):
            os.remove("test_file_new")
        if os.path.isfile("test_file_new.pyc"):
            os.remove("test_file_new.pyc")

        self.assertItemsEqual(self.scm.revisions_changing_file("non_existent_file"), [])
        write_into_file_at_path(create_patch_path, '#!/bin/sh\necho $PWD')  # We could pass -n to prevent the \n, but not all echo accept -n.
        actual_patch_contents = scm.create_patch()
        expected_patch_contents = """Index: test_dir2/test_file2
===================================================================
--- test_dir2/test_file2\t(nonexistent)
+++ test_dir2/test_file2\t(working copy)
@@ -0,0 +1 @@\n+test content
\\ No newline at end of file
"""
        self.assertEqual(expected_patch_contents, actual_patch_contents)
    def test_untracked_files(self):
        self._shared_test_untracked_files(self.scm)

    def test_discard_untracked_files(self):
        self._shared_test_discard_untracked_files(self.scm)


        write_into_file_at_path('.gitignore', '*.pyc')
        run_command(['git', 'add', '.gitignore'])
    def test_untracked_files(self):
        self._shared_test_untracked_files(self.tracking_scm)

        run_silent(['git', 'svn', 'clone', '-T', 'trunk', '--prefix', '', self.svn_repo_url, self.git_checkout_path])
        run_silent(['git', 'branch', '-m', 'trunk'])
        self.assertRaises(ScriptError, run_silent, ['git', 'svn', '--quiet', 'rebase'])  # Will fail due to a conflict leaving us mid-rebase.
        files = self.scm.changed_files('trunk..')  # git diff trunk..HEAD
        self.assertNotIn('test_file_commit1', files)
        self.assertNotIn('test_file_commit2', files)

        files = self.scm.changed_files('trunk^..')  # git diff trunk^..HEAD
        # .... is a hack for working copy changes to be included
        files = self.scm.changed_files('trunk....')  # git diff trunk
        self.assertNotIn('test_file_commit1', files)
        self.assertIn('test_file_commit2', files)

        files = self.scm.changed_files('trunk^....')  # git diff trunk^
        scm = Git(cwd=".", patch_directories=None, executive=MockExecutive(), filesystem=MockFileSystem())