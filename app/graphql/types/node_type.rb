module Types
  class NodeType < BaseObject
    field :id, ID, null: false
    field :title, String, null: true
    field :device_id, Integer, null: false
    field :temperature, Float, null: true

    def temperature
      object.values.last.temperature.to_f
    end
  end
end
