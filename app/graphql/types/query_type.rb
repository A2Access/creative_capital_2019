module Types
  class QueryType < Types::BaseObject
    field :current, [NodeType], null: false

    def current
      Node.includes(:values).all
    end
  end
end
