class CreateNodes < ActiveRecord::Migration[5.2]
  def change
    create_table :nodes do |t|
      t.integer :device_id, null: false
      t.text :title

      t.timestamps
    end
  end
end
