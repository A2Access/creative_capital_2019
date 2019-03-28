class CreateNodeValues < ActiveRecord::Migration[5.2]
  def change
    create_table :node_values do |t|
      t.references :node, index: true
      t.decimal :temperature, precision: 4, scale: 2
      t.decimal :humidity, precision: 5, scale: 2

      t.timestamps
    end
  end
end
