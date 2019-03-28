Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html

  resources :nodes do
    resource :data, controller: :node_values, only: :create
  end
end
