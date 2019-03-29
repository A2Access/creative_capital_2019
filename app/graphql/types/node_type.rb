module Types
  class NodeType < BaseObject
    field :id, ID, null: false
    field :title, String, null: true
    field :device_id, Integer, null: false
    field :temperature, Float, null: true
    field :x, Float, null: true
    field :y, Float, null: true

    def temperature
      object.values.last.temperature.to_f
    end

    def x
      object.x.to_f
    end

    def y
      object.x.to_f
    end
  end
end
