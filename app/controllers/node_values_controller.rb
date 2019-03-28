class NodeValuesController < ApplicationController
  before_action :load_node

  def create
    @node_value = @node.values.create!(node_value_params)

    render json: @node_value, status: :ok
  end

  private

  def load_node
    @node = Node.find_or_create_by(device_id: params[:node_id])
  end

  def node_value_params
    params.permit(:humidity, :temperature)
  end
end
