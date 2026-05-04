vim.keymap.set("n", "<leader>b", function()
    vim.cmd "split | terminal cmake -S . -B build && cmake --build build && build/ocr"
end, { desc = "[B]uild Project" })
