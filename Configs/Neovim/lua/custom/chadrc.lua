-- This is an example chadrc file , its supposed to be placed in /lua/custom dir
-- lua/custom/chadrc.lua

local M = {}

-- make sure you maintain the structure of `core/default_config.lua` here,
-- example of changing theme:

M.ui = {
   theme = "uwu",
}

M.plugins = {
   options = {
      lspconfig = {
         setup_lspconf = "custom.plugin_confs.lspconfig",
      },
   },
}

M.options = {
   tabstop = 4,
   shiftwidth = 4,
   expandtab = true
}

return M
