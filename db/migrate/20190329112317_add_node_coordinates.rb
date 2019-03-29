class AddNodeCoordinates < ActiveRecord::Migration[5.2]
  def change
    add_column :nodes, :x, :integer
    add_column :nodes, :y, :integer
  end
end
