local M = {}

M.setup_lsp = function(attach, capabilities)
   local lspconfig = require "lspconfig"

   lspconfig.clangd.setup{
      -- format on save
      on_attach = function(client)
         if client.resolved_capabilities.document_formatting then
            vim.cmd "autocmd BufWritePre <buffer> lua vim.lsp.buf.formatting_sync()"
         end
      end,
      capabilities = capabilities,
      cmd = { "clangd", "--header-insertion=never", "--background-index"},
   }

   lspconfig.pyright.setup{
      on_attach = attach,
      capabilities = capabilities,
   }
end

return M
