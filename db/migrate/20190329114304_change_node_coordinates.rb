class ChangeNodeCoordinates < ActiveRecord::Migration[5.2]
  def up
    change_table :nodes do |t|
      t.change :x, :decimal, precision: 5, scale: 2
      t.change :y, :decimal, precision: 5, scale: 2
    end
  end

  def down
    change_table :nodes do |t|
      t.change :x, :integer
      t.change :y, :integer
    end
  end
end
