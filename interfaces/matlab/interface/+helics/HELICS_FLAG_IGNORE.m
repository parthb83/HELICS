function v = HELICS_FLAG_IGNORE()
  persistent vInitialized;
  if isempty(vInitialized)
    vInitialized = helicsMEX(0, 47);
  end
  v = vInitialized;
end
