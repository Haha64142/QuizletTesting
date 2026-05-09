vim.keymap.set("n", "<leader>b", function()
    vim.cmd "split | terminal cmake -S . -B build && cmake --build build && build/textDataBuilder WW2.txt WW2-out.txt"
end, { desc = "[B]uild Project" })
