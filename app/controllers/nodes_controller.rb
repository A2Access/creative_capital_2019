class NodesController < ApplicationController
  before_action :load_node, only: :show

  def show
    render json: @node, status: :ok
  end

  def create
    @node = Node.create!(node_params)

    render json: @node, status: :ok
  end

  private

  def load_node
    @node = Node.find(params[:id])
  end

  def node_params
    params.permit(:title, :device_id)
  end
end
