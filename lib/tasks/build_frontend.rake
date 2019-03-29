task :build_frontend do
  system 'cd frontend; npm run build'
end

# cd fRake::Task['assets:precompile'].enhance ['build_frontend'] 
