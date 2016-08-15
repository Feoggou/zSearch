import os
import platform
import subprocess
import shutil

import unittest

# TODO: Use cmake to generate the BIN path
BIN_DIR = os.path.abspath("../../zSearch-build/bin")
APP_NAME = "cZSearch.exe" if platform.system() == "Windows" else "cZSearch"
APP_PATH = os.path.join(BIN_DIR, APP_NAME)
TEST_DATA = "TestData"


class TestLocalDir(unittest.TestCase):
    TEST_DATA_PATH = os.path.join(BIN_DIR, TEST_DATA)

    @classmethod
    def setUpClass(cls):
        assert os.path.exists(APP_PATH)

        os.chdir(BIN_DIR)
        if not os.path.exists(TEST_DATA):
            os.mkdir(TEST_DATA)

        os.chdir(TEST_DATA)

    @classmethod
    def clean_dir_contents(cls):
        os.chdir(os.path.dirname(cls.TEST_DATA_PATH))

        shutil.rmtree(cls.TEST_DATA_PATH)
        os.mkdir(cls.TEST_DATA_PATH)

        os.chdir(cls.TEST_DATA_PATH)

    @staticmethod
    def run_search_with_args(*args):
        completed_proc = subprocess.run([APP_PATH, *args], stdout=subprocess.PIPE, universal_newlines=True)
        return completed_proc.stdout

    def setUp(self):
        self.clean_dir_contents()

    def test_whenCurrentDir_isEmpty_searchAll_noFilter_returns_0Items(self):
        out_text = self.run_search_with_args()

        self.assertEqual("Items found: 0\n", out_text)

    def test_whenCurrentDir_hasOneItem_searchAll_noFilter_returns_1ItemName(self):
        os.mkdir("empty_dir")
        out_text = self.run_search_with_args()

        self.assertEqual(
            "empty_dir\n"
            "Items found: 1\n",
            out_text)


if __name__ == "__main__":
    unittest.main()
