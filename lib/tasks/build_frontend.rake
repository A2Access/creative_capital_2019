task :build_frontend do
  system 'cd frontend; npm run build'
end

Rake::Task['assets:precompile'].enhance ['build_frontend']
