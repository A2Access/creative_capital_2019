module Types
  class NodeType < BaseObject
    field :id, ID, null: false
    field :title, String, null: true
    field :device_id, Integer, null: false
  end
end
